#include <QApplication>
#include <QLabel>
#include <QMainWindow>
#include <QObject>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

import example_store;

class SignalHandler : public QObject {
    Q_OBJECT

    signals:
    void onStoreUpdate();
};

int main(int argc, char* argv[]) {

    auto app = new QApplication(argc, argv);
    Example::Store store;

    auto signal_handler = new SignalHandler();
    store.subscribe([signal_handler](){
        emit signal_handler->onStoreUpdate();
    });

    auto window = new QMainWindow();

    auto main_widget = new QWidget();
    window->setCentralWidget(main_widget);

    auto main_layout = new QVBoxLayout();
    main_widget->setLayout(main_layout);

    auto label = new QLabel();
    label->setAlignment(Qt:: AlignVCenter | Qt::AlignHCenter);
    {
        auto reader = store.reader();
        label->setText(std::to_string(reader.data().value).c_str());
    }
    main_layout->addWidget(label);
    QObject::connect(
        signal_handler,
        &SignalHandler::onStoreUpdate,
        label,
        [label, &store](){
            auto reader = store.reader();
            label->setText(std::to_string(reader.data().value).c_str());
        }
    );

    auto button_layout = new QHBoxLayout();
    main_layout->addLayout(button_layout);

    auto decrement_button = new QPushButton("-");
    button_layout->addWidget(decrement_button);
    QObject::connect(
        decrement_button,
        &QPushButton::clicked,
        app,
        [&store](){
            store.dispatch(Example::Decrement {1});
        }
    );

    auto increment_button = new QPushButton("+");
    button_layout->addWidget(increment_button);
    QObject::connect(
        increment_button,
        &QPushButton::clicked,
        app,
        [&store](){
            store.dispatch(Example::Increment {1});
        }
    );


    window->show();
    return app->exec();
}

#include "qt_app.moc"
