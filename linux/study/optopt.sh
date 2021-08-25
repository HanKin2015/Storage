# 第一个冒号表示忽略错误，第二个冒号表示i后面必须要有自己的参数
# 如 $0 -i 88 -u 99 33 44
while getopts ":i:u" opt
do
    case ${opt} in
        i)
            echo "$OPTARG"
            echo "$OPTIND"
            echo "$opt"
            ;;
        u)
            echo "$opt"
            echo "$OPTARG" # 因为它没有自己的参数
            echo "$OPTIND"
            ;;
        *)
            echo "unknow option"
            ;;
    esac
done
