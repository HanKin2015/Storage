#!/usr/bin/perl

# 增加严格标准会有错误警告:Unquoted string "d" may clash with future reserved word
use strict;
use warnings;

open _d, "< test.txt";

# 全部读取
#print <d>;

# 逐行读取
while(<_d>){
	print "--------------";
	print $_;
}

close _d;

# 覆盖写入
#open d, "> test.txt";

# 追加写入
open _d, ">> test.txt";
print _d "hello,world\nsee you\n";

my $str = "123456\n";
print _d "$str\n";

close _d;
