#include "../common.h"

#include <cstdio>
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include <boost/system/system_error.hpp>
#include <memory>

using boost::asio::ip::tcp;

class TtcpServerConnection : public std::enable_shared_from_this<TtcpServerConnection>, boost::noncopyable {
public:
    TtcpServerConnection(const boost::asio::executor& executor) :
        socket_(executor), count_(0), payload_(nullptr), ack_(0) {
        sessionMessage_.number = 0;
        sessionMessage_.length = 0;
    }

    ~TtcpServerConnection() {
        ::free(payload_);
    }

    tcp::socket& socket() { return socket_; }

    void start() {
        std::ostringstream oss;
        oss << socket_.remote_endpoint();
        doReadSession();
    }
private:
    void doReadSession() {
        auto self(shared_from_this());
        boost::asio::async_read(
            socket_, boost::asio::buffer(&sessionMessage_, sizeof(sessionMessage_)),
            [this, self](const boost::system::error_code& error, size_t len) {
                if (!error && len == sizeof(sessionMessage_)) {
                    sessionMessage_.number = ntohl(sessionMessage_.number);
                    sessionMessage_.length = ntohl(sessionMessage_.length);
                    printf("receive number = %d\nreceive length = %d\n", sessionMessage_.number, sessionMessage_.length);
                    const int total_len = static_cast<int>(sizeof(int32_t) + sessionMessage_.length);
                    payload_ = static_cast<PayloadMessage*>(::malloc(total_len));
                    doReadLength();
                }
                else {
                    printf("read session message: %s", error.message().c_str());
                }
            }
        );
    }

    void doReadLength()
    {
        auto self(shared_from_this());
        payload_->length = 0;
        boost::asio::async_read(
            socket_, boost::asio::buffer(&payload_->length, sizeof payload_->length),
            [this, self](const boost::system::error_code& error, size_t len)
            {
                if (!error && len == sizeof payload_->length)
                {
                    payload_->length = ntohl(payload_->length);
                    doReadPayload();
                }
                else
                {
                    //LOG_ERROR << "read length: " << error.message();
                }
            });
    }

    void doReadPayload() {
        assert(payload_->length == sessionMessage_.length);
        // if(payload_->length != sessionMessage_.length) {
        //     printf("%d, %d\n", payload_->length, sessionMessage_.length);
        // }
        auto self(shared_from_this());
        boost::asio::async_read(
            socket_, boost::asio::buffer(&payload_->data, payload_->length),
            [this, self](const boost::system::error_code& code, size_t len) {
                if (!code && len == static_cast<size_t>(payload_->length)) {
                    doWriteAck();
                }
                else {
                    printf("read payload data: %s\n", code.message().c_str());
                }
            }
        );
    }

    void doWriteAck() {
        auto self(shared_from_this());
        ack_ = htonl(payload_->length);
        boost::asio::async_write(socket_, boost::asio::buffer(&ack_, sizeof ack_),
            [this, self](const boost::system::error_code& error, size_t len) {
                if (!error && len == sizeof ack_) {
                    if (++count_ < sessionMessage_.number) {
                        doReadLength();
                    }
                    else {
                        printf("done.\n");
                    }
                }
                else {
                    printf("write ack: %s\n", error.message().c_str());
                }
            }
        );
    }

    tcp::socket socket_;
    int count_;
    struct SessionMessage sessionMessage_;
    struct PayloadMessage* payload_;
    int32_t ack_;
};

typedef std::shared_ptr<TtcpServerConnection> TtcpServerConnectionPtr;

void doAccept(tcp::acceptor& acceptor) {
    TtcpServerConnectionPtr new_connection(new TtcpServerConnection(acceptor.get_executor()));

    acceptor.async_accept(
        new_connection->socket(),
        [&acceptor, new_connection](boost::system::error_code error) {
            if (!error) {
                new_connection->start();
            }
            doAccept(acceptor);
        }
    );
}

void receive(const Options& opt) {
    try {
        boost::asio::io_service io_service;
        tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), opt.port));
        doAccept(acceptor);
        io_service.run();
    }
    catch (std::exception& e) {
        printf("%s", e.what());
    }
}

int main(int argc, char** argv) {
    Options opt;
    if (parseCommandLine(argc, argv, &opt)) {
        if (opt.receive) {
            receive(opt);
        }
    }
    return 0;
}