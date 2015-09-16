#include <stdio.h>
#include <stdlib.h>
#include "android_filesystem_config.h"

// from http://selinuxproject.org/page/NB_SEforAndroid_2

int main(int argc, char **argv)
{
	uid_t uid;

	if (argc != 2) {
		printf("Converts an Android uid to username\n");
		printf("usage: %s uid\n\n", argv[0]);
		exit(1);
	}

	uid = atoi(argv[1]);
	uid_t appid = uid % AID_USER;
	uid_t userid = uid / AID_USER;

	if (appid >= AID_ISOLATED_START) {
		printf("username: u%u_i%u\n", userid, appid - AID_ISOLATED_START);
	} else if (userid == 0 && appid >= AID_SHARED_GID_START) {
		printf("username: all_a%u\n", appid - AID_SHARED_GID_START);
	} else if (appid < AID_APP) {
		for (size_t n = 0; n < android_id_count; n++) {
			if (android_ids[n].aid == appid) {
				printf("username: u%u_%s\n", userid, android_ids[n].name);
				printf("Note that only \"%s\" will be shown in 'ps' etc.\n", android_ids[n].name);
				exit(0);
			}
		}
		printf("Failed - invalid uid\n");
	} else {
		printf("username: u%u_a%u\n", userid, appid - AID_APP);
	}
	exit(0);
}
