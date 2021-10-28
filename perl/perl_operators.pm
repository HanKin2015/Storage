#!/usr/bin/perl

print "hello world\n";

my $osname = "win764";

print "osname: $osname\n";

if ( $osname ne "win7" && $osname ne "win764" ) {
    print "add xhci\n";
} else {
    print "use ehci\n";
}

my $flag = True;

# 注意：使用state操作符时，一定要加上版本限制use 5.010，否则会失效
# 在Perl中想要使用state，必须在文件开头加上 use feature qw(state); 或者 use 5.010; 因为state功能是在5.010版本中才开始提供的
#use 5.010;
#use 5.22.1;
use 5.14.2;

=opt
if ($flag) {
    our $a   = "i am a";
    my $b    = "i am b";
    state $c = "i am c";
    local $d = "i am d";
    print "a:$a, b:$b, c:$c, d:$d\n";
}

print "\nglobal\n";
print "a:$a, b:$b, c:$c, d:$d\n";
=cut

if ($flag) {
    our $a = "i am aaaa";
}

if ($flag) {
    print "$a\n";
}

=opt
何苦为难自己,在全局声明my变量不就是全局变量了....

hello world
osname: win764
use ehci
a:i am a, b:i am b, c:i am c, d:i am d

global
a:i am a, b:, c:, d:
=cut