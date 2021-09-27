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

my $person = {
    name => 'hj',
    sex  => 'man',
    age  => 32
};
print_person_info($person);
