#include <opencv2/opencv.hpp>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/StreamSocket.h>
#include <Poco/Net/SocketAddress.h>
#include <iostream>
#include <vector>

using namespace Poco::Net;
using namespace std;
using namespace cv;

int main() {
    try {
        ServerSocket server(12345);
        cout << "✅ Server listening on port 12345...\n";

        StreamSocket client = server.acceptConnection();
        cout << "✅ Client connected.\n";

        while (true) {
            int size;
            int received = client.receiveBytes(&size, sizeof(int));
            if (received != sizeof(int)) break;

            vector<uchar> buffer(size);
            int totalReceived = 0;
            while (totalReceived < size) {
                int bytes = client.receiveBytes(buffer.data() + totalReceived, size - totalReceived);
                if (bytes <= 0) break;
                totalReceived += bytes;
            }

            Mat img = imdecode(buffer, IMREAD_COLOR);
            if (!img.empty()) {
                imshow("Received Frame", img);
                if (waitKey(1) == 27) break;
            }
        }

        client.close();
        server.close();
        cout << "❌ Connection closed.\n";
    } catch (exception& e) {
        cerr << "❌ Error: " << e.what() << endl;
        return 1;
    }

    return 0;
}
