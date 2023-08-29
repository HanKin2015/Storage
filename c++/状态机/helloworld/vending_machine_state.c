/**
* 文 件 名: vending_machine_state.c
* 文件描述: 模拟一个自动售货机的状态
* 作    者: HanKin
* 创建日期: 2023.08.21
* 修改日期：2023.08.21
*
* Copyright (c) 2023 HanKin. All rights reserved.
*/
#include <stdio.h>

typedef enum {
    IDLE,
    COIN_INSERTED,
    ITEM_SELECTED,
    ITEM_DISPENSED,
    CHANGE_DISPENSED
} VendingMachineState;

VendingMachineState state = IDLE;

// 用于插入硬币。在这个函数中，如果当前状态为 IDLE，则将状态改为 COIN_INSERTED，并输出一条消息表示硬币已插入；否则输出一条消息表示操作无效。
void insert_coin()
{
    if (state == IDLE) {
        state = COIN_INSERTED;
        printf("Coin inserted.\n");
    } else {
        printf("Invalid operation.\n");
    }
}

// 用于选择商品。在这个函数中，如果当前状态为 COIN_INSERTED，则将状态改为 ITEM_SELECTED，并输出一条消息表示商品已选择；否则输出一条消息表示操作无效。
void select_item()
{
    if (state == COIN_INSERTED) {
        state = ITEM_SELECTED;
        printf("Item selected.\n");
    } else {
        printf("Invalid operation.\n");
    }
}

// 用于出售商品。在这个函数中，如果当前状态为 ITEM_SELECTED，则将状态改为 ITEM_DISPENSED，并输出一条消息表示商品已出售；否则输出一条消息表示操作无效。
void dispense_item()
{
    if (state == ITEM_SELECTED) {
        state = ITEM_DISPENSED;
        printf("Item dispensed.\n");
    } else {
        printf("Invalid operation.\n");
    }
}

// 用于找零。在这个函数中，如果当前状态为 ITEM_DISPENSED，则将状态改为 CHANGE_DISPENSED，并输出一条消息表示找零已发放；否则输出一条消息表示操作无效。
void dispense_change()
{
    if (state == ITEM_DISPENSED) {
        state = CHANGE_DISPENSED;
        printf("Change dispensed.\n");
    } else {
        printf("Invalid operation.\n");
    }
}

// 用于取消交易。在这个函数中，如果当前状态为 COIN_INSERTED 或 ITEM_SELECTED，则将状态改为 IDLE，并输出一条消息表示交易已取消；否则输出一条消息表示操作无效。
void cancel_transaction()
{
    if (state == COIN_INSERTED || state == ITEM_SELECTED) {
        state = IDLE;
        printf("Transaction cancelled.\n");
    } else {
        printf("Invalid operation.\n");
    }
}

VendingMachineState get_state()
{
    return state;
}

int main()
{
    printf("%d\n", get_state());  // 输出 "0"，表示 IDLE 状态

    insert_coin();

    printf("%d\n", get_state());  // 输出 "1"，表示 COIN_INSERTED 状态

    select_item();

    printf("%d\n", get_state());  // 输出 "2"，表示 ITEM_SELECTED 状态

    dispense_item();

    printf("%d\n", get_state());  // 输出 "3"，表示 ITEM_DISPENSED 状态

    dispense_change();

    printf("%d\n", get_state());  // 输出 "4"，表示 CHANGE_DISPENSED 状态

    cancel_transaction();

    printf("%d\n", get_state());  // 输出 "0"，表示 IDLE 状态

    return 0;
}
/*
0
Coin inserted.
1
Item selected.
2
Item dispensed.
3
Change dispensed.
4
Invalid operation.
4
*/
