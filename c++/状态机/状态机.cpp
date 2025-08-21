#include <iostream>
#include <string>

// 定义状态
enum class OrderState {
    PENDING_PAYMENT,  // 待支付
    PAID,             // 已支付
    SHIPPED,          // 已发货
    DELIVERED,        // 已送达
    CANCELLED         // 已取消
};

// 定义事件
enum class Event {
    PAY,           // 支付
    SHIP,          // 发货
    DELIVER,       // 送达
    TIMEOUT,       // 超时未支付
    REFUND         // 退款（简化示例）
};

// 状态机处理函数
OrderState handleEvent(OrderState currentState, Event event) {
    switch (currentState) {
        case OrderState::PENDING_PAYMENT:
            if (event == Event::PAY) {
                std::cout << "订单已支付，生成物流单\n";
                return OrderState::PAID;
            } else if (event == Event::TIMEOUT) {
                std::cout << "订单超时，已取消\n";
                return OrderState::CANCELLED;
            }
            break;
        
        case OrderState::PAID:
            if (event == Event::SHIP) {
                std::cout << "订单已发货\n";
                return OrderState::SHIPPED;
            } else if (event == Event::REFUND) {
                std::cout << "订单已退款，状态改为取消\n";
                return OrderState::CANCELLED;
            }
            break;
        
        case OrderState::SHIPPED:
            if (event == Event::DELIVER) {
                std::cout << "订单已送达\n";
                return OrderState::DELIVERED;
            }
            break;
        
        // 其他状态的事件处理...
        default:
            std::cout << "无效事件\n";
            return currentState;
    }
    return currentState;
}

int main() {
    OrderState state = OrderState::PENDING_PAYMENT;
    state = handleEvent(state, Event::PAY);         // 待支付 → 已支付
    state = handleEvent(state, Event::SHIP);        // 已支付 → 已发货
    state = handleEvent(state, Event::DELIVER);     // 已发货 → 已送达
    return 0;
}