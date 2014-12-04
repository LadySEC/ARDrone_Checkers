#include <stdio.h>
#include <stdlib.h>
#include "../log.h"

int main(int argc, char * argv[]) {
	if (argc != 3) {
		printf("Usage : %s <log_file> <log_level>\nwhere log_level is from 1 (ERROR) to 5 (DEBUG)\n", argv[0]);
		return -1;
	} else {
		LOG_Init(argv[1], atoi(argv[2]));
		LOG_Write("Niveau de log global du programme : %s", argv[2]);
		LOG_WriteLevel(LOG_ERROR, "Log de niveau ERROR");
		LOG_WriteLevel(LOG_WARN, "Log de niveau WARNING");
		LOG_WriteLevel(LOG_INFO, "Log de niveau INFO");
		LOG_WriteLevel(LOG_DEBUG, "Log de niveau DEBUG");
		LOG_End();
		return 0;
	}
}