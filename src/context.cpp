#include "context.h"
#include "settings.h"
#include "cpp_base_lib/msg_notifier.h"
namespace yk {

std::shared_ptr<Context> Context::Make() {
    return std::make_shared<Context>();
}

Context::Context() {
    settings_ = Settings::Instance();
}

bool Context::Init() {
    iopool_ = std::make_shared<asio2::iopool>();
    iopool_->start();

    net_iopool_ = std::make_shared<asio2::iopool>(2);
    net_iopool_->start();

    timer_ = std::make_shared<asio2::timer>();

    msg_thread_ = Thread::Make("yk message thread", 1024);
    msg_thread_->Poll();

    msg_notifier_ = MessageNotifier::Make();

    InitTimers();

    return true;
}

void Context::InitTimers() {

}

void Context::Exit() {

}
void Context::PostTask(std::function<void()>&& task) {
    iopool_->post(std::move(task));
}
void Context::PostUITask(std::function<void()>&& task) {
    QMetaObject::invokeMethod(this, [t = std::move(task)]() {
        t();
    });
}
Settings* Context::GetSettings() {
    return settings_;
}

std::shared_ptr<MessageNotifier> Context::GetMessageNotifier() {
    return msg_notifier_;
}

std::shared_ptr<MessageListener> Context::CreateMessageListener() {
    return msg_notifier_->CreateListener();
}



}