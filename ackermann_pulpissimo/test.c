/* 
 * Implementation of the Ackermann function with Pulpissimo SDK.
 * The function implementation is adapted from T. Austin's Bringup-Bench.
 */

#include "pmsis.h"

#define MAX 5

#define MAX_X 0xFF
#define MAX_Y 0xFF
#define MAX_DEPTH 0xFFFF

static int a[MAX_X][MAX_Y];
static int depth;
static int max_depth;


int ack(int x, int y) {
	depth++;
	if(depth > MAX_DEPTH) {
		printf("Maximum stack depth %d exceeded. Abort.\n", MAX_DEPTH);
		return -1;
	}
	if(x >= MAX_X) {
		printf("Maximum x value %d exceeded. Abort.\n", MAX_X);
        return -1;
	}
	if(y >= MAX_Y) {
		printf("Maximum y value %d exceeded. Abort.\n", MAX_Y);
		return -1;
	}
	if(a[x][y]) return a[x][y];
	if(y==0) return a[x][0] = x + 1;
	if(x==0) return a[0][y] = ack(1, y - 1);
    return a[x][y] = ack(ack(x - 1, y), y - 1);
}	

static int test_entry() {
	int y, k, _ack;
    max_depth = 0;

    for(k = 0; k <= MAX; k++) {
        printf("\nx + y = %d:\n\n", k);
        for(y = 0; y <= k; y++) {
            depth = 0;
            _ack = ack(k - y, y);
            if(_ack > 0) {
                printf("A(%d, %d) = %d\n", k - y, y, _ack);
                if(depth > max_depth) max_depth = depth;
            }
        }
    }

    printf("Max recursive depth = %u\n", max_depth);

    return 0;
}

static void test_kickoff(void *arg) {
    int ret = test_entry();
    pmsis_exit(ret);
}

int main() {
    return pmsis_kickoff((void *)test_kickoff);
}