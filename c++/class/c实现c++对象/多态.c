/*******************************************************************************
* 文 件 名: 多态.c
* 文件描述: 模拟 “多态”（同一接口不同实现）
* 备    注: 可以通过函数指针 + 父类指针模拟（不同子类实现同一函数指针）
* 作    者: HanKin
* 创建日期: 2025.09.12
* 修改日期：2025.09.12
*
* Copyright (c) 2025 HanKin. All rights reserved.
*******************************************************************************/
// 父类：Shape
typedef struct {
    float (*area)(const void* self);  // 父类方法
} Shape;

// 子类：Circle（继承自Shape）
typedef struct {
    Shape parent;  // 父类部分（必须是第一个成员）
    float radius;  // 子类特有数据
} Circle;

// 子类实现父类的area方法
float circle_area(const void* self) {
    const Circle* c = (const Circle*)self;
    return 3.14f * c->radius * c->radius;
}

// 子类构造函数（初始化父类方法）
Circle* circle_create(float radius) {
    Circle* c = (Circle*)malloc(sizeof(Circle));
    c->parent.area = circle_area;  // 绑定父类方法
    c->radius = radius;
    return c;
}

// 父类接口（通过父类指针调用子类方法）
float shape_area(const Shape* s) {
    return s->area(s);  // 实际调用的是子类实现
}

int main() {
    Circle* c = circle_create(2.0f);
    // 通过父类指针调用（模拟多态的基础）
    printf("Area: %.2f\n", shape_area((Shape*)c));
    free(c);
    return 0;
}