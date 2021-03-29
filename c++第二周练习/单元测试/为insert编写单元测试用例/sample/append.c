int main(int argc, char *argv[])
{
    int i;
    for (i = 0; i < OJ_RUN_ROUND_NUM; ++i) {
        ut_run();
    }
    test_clear(&s_root);
    return 0;
}
