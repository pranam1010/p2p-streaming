#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    std::cout << "📷 Trying to open camera using cv::VideoCapture(0)...\n";

    cv::VideoCapture cap(0, cv::CAP_ANY);
    if (!cap.isOpened()) {
        std::cerr << "❌ Failed to open camera. Check backend support and device availability.\n";

        std::cout << "Available backends:\n";
        auto backends = cv::videoio_registry::getBackends();
        for (auto backend : backends) {
            std::cout << " - " << cv::videoio_registry::getBackendName(backend) << "\n";
        }

        return -1;
    }

    std::cout << "✅ Camera opened successfully. Showing feed...\n";

    cv::Mat frame;
    while (true) {
        cap >> frame;
        if (frame.empty()) break;
        cv::imshow("Camera Feed", frame);
        if (cv::waitKey(10) == 27) break;
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
