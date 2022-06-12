#include "log.h"


static FILE *logfile;

static const char *levelStrings[] = {
	"TRACE", "DEBUG", "INFO ", "WARN ", "ERROR", "FATAL"
};

int log_open() {
	//open file
	logfile = fopen("logfile.txt", "a");
	if (logfile == NULL) {
		return -1;
	}
	return 0;
	//return -1 for failure
}

void log_close() {
	fclose(logfile);
}

void log_log(int level, const char *file, int line, const char *fmt, ...) {
	log_open();

	if (level >= LOG_LEVEL) {
		//print time stamp
		time_t rawtime = time(NULL);
		if (rawtime == -1) {
			fprintf(logfile, "Failed to get time ");
		}
		else {
			struct tm *timeNow = localtime(&rawtime);
			fprintf(logfile, "%02d:%02d:%02d %02d-%02d-%04d ", timeNow->tm_hour, timeNow->tm_min, timeNow->tm_sec, timeNow->tm_mon, timeNow->tm_mday, timeNow->tm_year + 1900);
		}
		

		//print log level
		fprintf(logfile, "[%s] ", levelStrings[level]);

		//print file name
		fprintf(logfile, "%s", stripPath(file));

		//print line number
		fprintf(logfile, ":%d ", line);

		//deal with variable arguments here
		va_list valist;
		va_start(valist, fmt);		
		vfprintf(logfile, fmt, valist);

		va_end(valist);
		//end the line
		//printString("\r\n");
		fprintf(logfile, "\n");
	}
	log_close();
}

//helper functions
const char *stripPath(const char *filename) {
	int position = 0;
	int i = 0;
	while (filename[i]) {
		if (filename[i] == '/') {
			position = i;
		}
		i++;
	}
	return &filename[position + 1];
}