#include "detect.h"

#ifdef __cplusplus
extern "C" {
#endif

static char TAG[] = "UninstalledObserverActivity.init";
static jboolean isCopy = JNI_TRUE;

static const char APP_DIR[] = "/data/data/com.example.deletedetect";
static const char APP_FILES_DIR[] = "/data/data/com.example.deletedetect/files";
static const char APP_OBSERVED_FILE[] = "/data/data/com.example.deletedetect/files/observedFile";
static const char APP_LOCK_FILE[] = "/data/data/com.example.deletedetect/files/lockFile";


JNIEXPORT int JNICALL Java_com_example_deletedetect_UninstallObserver_init(JNIEnv *env, jobject obj, jstring userSerial){
	jstring tag = (*env)->NewStringUTF(env, TAG);

	LOG_DEBUG((*env)->GetStringUTFChars(env, tag, &isCopy), (*env)->GetStringUTFChars(env, (*env)->NewStringUTF(env, "init observer"), &isCopy));

	pid_t pid = fork();
	if(pid < 0){
		LOG_ERROR((*env)->GetStringUTFChars(env, tag, &isCopy), (*env)->GetStringUTFChars(env, (*env)->NewStringUTF(env, "fork failed!!!"), &isCopy));

		exit(1);
	}else if(pid == 0){
		FILE *p_filesDir = fopen(APP_FILES_DIR, "r");
		if(p_filesDir == NULL){
			int filesDirRet = mkdir(APP_FILES_DIR, S_IRWXU | S_IRWXG | S_IXOTH);
			if(filesDirRet == -1){
				LOG_ERROR((*env)->GetStringUTFChars(env, tag, &isCopy), (*env)->GetStringUTFChars(env, (*env)->NewStringUTF(env, "mkdir failed!!!"), &isCopy));

				exit(1);
			}
		}


		FILE *p_observedFile = fopen(APP_OBSERVED_FILE, "r");
		if(p_observedFile == NULL){
			p_observedFile = fopen(APP_OBSERVED_FILE, "w");
		}

		fclose(p_observedFile);

		int lockFileDescriptor = open(APP_LOCK_FILE, O_RDONLY);
		if(lockFileDescriptor == -1){
			lockFileDescriptor = open(APP_LOCK_FILE, O_CREAT);

		}

		int lockRet = flock(lockFileDescriptor, LOCK_EX | LOCK_NB);
		if(lockRet == -1){
			LOG_DEBUG((*env)->GetStringUTFChars(env, tag, &isCopy), (*env)->GetStringUTFChars(env, (*env)->NewStringUTF(env, "observed by another process"), &isCopy));

			exit(0);
		}
		LOG_DEBUG((*env)->GetStringUTFChars(env, tag, &isCopy), (*env)->GetStringUTFChars(env, (*env)->NewStringUTF(env, "observed by child process"), &isCopy));

		void *p_buf = malloc(sizeof(struct inotify_event));
		if(p_buf == NULL){
			LOG_ERROR((*env)->GetStringUTFChars(env, tag, &isCopy), (*env)->GetStringUTFChars(env, (*env)->NewStringUTF(env, "malloc failed!!!"), &isCopy));

			exit(1);
		}

		int maskStrLength = 7 + 10 + 1;
		char *p_maskStr = malloc(maskStrLength);

		if(p_maskStr == NULL){
			free(p_buf);

			LOG_ERROR((*env)->GetStringUTFChars(env, tag, &isCopy), (*env)->GetStringUTFChars(env, (*env)->NewStringUTF(env, "malloc failed!!!"), &isCopy));

			exit(1);
		}

		LOG_DEBUG((*env)->GetStringUTFChars(env, tag, &isCopy), (*env)->GetStringUTFChars(env, (*env)->NewStringUTF(env, "start observe"), &isCopy));

		int fileDescriptor = inotify_init();
		if(fileDescriptor < 0){
			free(p_buf);
			free(p_maskStr);
			LOG_ERROR((*env)->GetStringUTFChars(env, tag, &isCopy), (*env)->GetStringUTFChars(env, (*env)->NewStringUTF(env, "inotify_init failed!!!"), &isCopy));

			exit(1);
		}

		int watchDescriptor = inotify_add_watch(fileDescriptor, APP_OBSERVED_FILE, IN_ALL_EVENTS);
		if(watchDescriptor < 0){
			free(p_buf);
			free(p_maskStr);

			LOG_ERROR((*env)->GetStringUTFChars(env, tag, &isCopy), (*env)->GetStringUTFChars(env, (*env)->NewStringUTF(env, "inotify_add_watch failed!!!"), &isCopy));

			exit(1);
		}

		while(1){
			size_t readBytes = read(fileDescriptor, p_buf, sizeof(struct inotify_event));

			snprintf(p_maskStr, maskStrLength, "mask-0x%x\0", ((struct inotify_event *) p_buf)->mask);

			LOG_DEBUG((*env)->GetStringUTFChars(env, tag, &isCopy), (*env)->GetStringUTFChars(env, (*env)->NewStringUTF(env, p_maskStr), &isCopy));

			if(IN_DELETE_SELF == ((struct inotify_event *) p_buf)->mask){
				FILE *p_appDir = fopen(APP_DIR, "r");
				if(p_appDir == NULL){
					inotify_rm_watch(fileDescriptor, watchDescriptor);

					break;
				}else{
					fclose(p_appDir);

					FILE *p_observedFile = fopen(APP_OBSERVED_FILE, "w");
					fclose(p_observedFile);

					int watchDescriptor = inotify_add_watch(fileDescriptor, APP_OBSERVED_FILE, IN_ALL_EVENTS);
					if(watchDescriptor < 0){
						free(p_buf);
						free(p_maskStr);

						LOG_ERROR((*env)->GetStringUTFChars(env, tag, &isCopy), (*env)->GetStringUTFChars(env, (*env)->NewStringUTF(env, "inotify_add_watch failed!!!"), &isCopy));

						exit(1);
					}
				}
			}
		}

		free(p_buf);
		free(p_maskStr);

		LOG_DEBUG((*env)->GetStringUTFChars(env, tag, &isCopy), (*env)->GetStringUTFChars(env, (*env)->NewStringUTF(env, "stop observe"), &isCopy));

		if(userSerial == NULL){
			execlp("am", "am", "start", "-a", "android.intent.action.VIEW", "-d", "http://www.tifen.com", (char *) NULL);
		}else{
			execlp("am", "am", "start", "--user", (*env)->GetStringUTFChars(env, userSerial, &isCopy), "-a", "android.intent.action.VIEW", "-d", "http://www.tifen.com", (char *) NULL);
		}

		LOG_ERROR((*env)->GetStringUTFChars(env, tag, &isCopy), (*env)->GetStringUTFChars(env, (*env)->NewStringUTF(env, "exec AM command failed!!!"), &isCopy));
	}else{
		return pid;
	}
}

#ifdef __cplusplus
}
#endif