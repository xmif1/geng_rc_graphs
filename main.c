#include "gtools.h"

long r, c;

int PRUNE(graph *g, int n, int maxn) {
    int i, j, k, v, e, nsub;
    setword *gv, *wgi;

    DYNALLSTAT(boolean,perm,perm_sz);
    DYNALLOC1(int,perm,perm_sz,n,"nbrhoodg");

    for (v = 0, gv = GRAPHROW(g,0,1); v < n; ++v, gv += 1) {
        if (ISELEMENT(gv, n - 1) || v == n - 1) {
            nsub = e = 0;

            for (i = 0; i < n; ++i) {
                if (ISELEMENT(gv, i) && i != v) perm[nsub++] = i;
            }

            for (i = 0; i < nsub; ++i) {
                wgi = GRAPHROW(g, perm[i], 1);
                for (j = 0; j < nsub; ++j) {
                    k = perm[j];
                    if (ISELEMENT(wgi,k)) e++;
                }
            }

            if (e > 2*c || nsub == r && e < 2*c || nsub > r) {
                DYNFREE(perm, perm_sz);
                return -1;
            }
        }
    }

    DYNFREE(perm, perm_sz);

    return 0;
}

int GENG_MAIN(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    if (argc < 4) exit(1);

    int geng_argc;
    char nstring[6]; /* string to put n into */
    char dstring[6];  /* string to put d into */
    char Dstring[6];  /* string to put D into */
    char *geng_argv[7]; /* At least one bigger than geng_argc */

    r = strtol(argv[1], NULL, 10);
    c = strtol(argv[2], NULL, 10);

    /* Set up geng argument list. */

    sprintf(nstring,"%s", argv[3]);
    sprintf(dstring,"-d%s", argv[1]);
    sprintf(Dstring,"-D%s", argv[1]);

    geng_argv[0] = "geng";
    geng_argv[1] = "-q";
    geng_argv[2] = "-c";
    geng_argv[3] = dstring;
    geng_argv[4] = Dstring;
    geng_argv[5] = nstring;
    geng_argv[6] = NULL;
    geng_argc = 6;

    GENG_MAIN(geng_argc,geng_argv);

    exit(0);
}
