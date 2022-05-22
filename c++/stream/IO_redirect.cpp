#include <iostream>
#include <cstdio>
using namespace std;

int main()
{
    FILE *in_stream = freopen("input.txt", "r", stdin);
    FILE *out_stream = freopen ("output.txt", "w", stdout);

    if (in_stream == NULL) {
        fprintf(stderr, "error redirecting stdin\n");
        return -1;
    }
    if (in_stream == NULL) {
        fprintf(stderr, "error redirecting stdout\n");
        return -1;
    }

    int a, b;
    cin >> a >> b;
    cout << a << ' ' << b << endl;
    cout << a + b << endl;

    fclose(stdin);
    fclose(stdout);
    return 0;
}
