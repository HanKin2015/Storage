#!/usr/bin/perl -w

# 求和函数，传入xy值
sub sum_func {
    my ($x, $y) = @_;
    my $z = $x + $y;
    print("x+y=$z\n");
}
sum_func(2, 3);

# 输出个人信息
sub print_person_info {
    my ($person) = @_;

    my $name = $person->{ "name" };
    my $sex  = $person->{ "sex" };
    my $age  = $person->{ "age" };

    print("name: $name, sex: $sex, age: $age\n");
}
%person = ("name", "hj", "sex"=>"man", "age", 32); 
my $per1 = {
    "name"=>"hj",
    "sex" =>"man",
    "age" =>32
};
my $per2 = {
    name=>"hj",
    sex =>"man",
    age =>32
};
my $per3 = {
    name => 'hj',
    sex  => 'man',
    age  => 32
};
#print_person_info(%person);
print_person_info($per1);
print_person_info($per2);
print_person_info($per3);


print("name: $person{'name'}, sex: $person{'sex'}, age: $person{'age'}\n");
print("name: $person{\"name\"}, sex: $person{\"sex\"}, age: $person{\"age\"}\n");



print "文件名 ". __FILE__ . "\n";
print "行号 " . __LINE__ ."\n";
print "包名 " . __PACKAGE__ ."\n";
 
# 无法解析
print "__FILE__ __LINE__ __PACKAGE__\n";

$smile  = v9786;
$foo    = v102.111.111;
$martin = v77.97.114.116.105.110; 

print "smile = $smile\n";
print "foo = $foo\n";
print "martin = $martin\n";
