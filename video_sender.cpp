#include <opencv2/opencv.hpp>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketAddress.h>
#include <iostream>
#include <thread>
#include <chrono>

using namespace Poco::Net;
using namespace cv;
using namespace std;

int main() {
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        cerr << "Error: Could not open the camera.\n";
        return -1;
    }

    try {
        SocketAddress receiverAddr("127.0.0.1", 12345);
        StreamSocket socket;
        socket.connect(receiverAddr);

        Mat frame;
        vector<uchar> buffer;

        while (true) {
            cap >> frame;
            if (frame.empty()) {
                cerr << "Warning: Captured empty frame.\n";
                continue;
            }

            imencode(".jpg", frame, buffer);
            int size = static_cast<int>(buffer.size());

            socket.sendBytes(&size, sizeof(int));
            socket.sendBytes(buffer.data(), size);
            cout << "Sent frame of size: " << size << " bytes\n";

            this_thread::sleep_for(chrono::milliseconds(100));
        }

        socket.close();
    } catch (const exception& e) {
        cerr << "Send error: " << e.what() << endl;
    }

    cap.release();
    return 0;
}
