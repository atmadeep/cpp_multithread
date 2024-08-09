#include <condition_variable>
#include <mutex>
#include <opencv2/opencv.hpp>
#include <queue>
#include <thread>

// queues for consumer producer model.
std::queue<cv::Mat> capture_Queue;
std::queue<cv::Mat> process_Queue;

// mutex locks for 
std::mutex capture_Mutex;
std::mutex process_Mutex;

std::condition_variable capture_CondVar;
std::condition_variable process_CondVar;

bool done = false;

void captureImage() {
  // Open default camera @ id = 0
  cv::VideoCapture cap(0); 
  cv::Mat frame;
  // Return error if camera is not opened.
  if (!cap.isOpened()) {
    std::cerr << "Error: Could not open camera." << std::endl;
    return;
  }

  // The camera might send empty frames.
  while (!done) {
    cap >> frame;
    if (frame.empty()) {
      std::cerr << "Error: Captured empty frame." << std::endl;
      continue;
    }

    {
      // Capture lock for 1st queue i.e capture_Queue
      std::lock_guard<std::mutex> lock(capture_Mutex);
      capture_Queue.push(frame);
    } // The lock_guard is released as soon as it goes out of scope.

    capture_CondVar.notify_one();
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}

void processImage() {
  while (!done) {
    cv::Mat frame;

    {
      std::unique_lock<std::mutex> lock(capture_Mutex);
      // The capture_Mutex is used for capture_Queue object.
      capture_CondVar.wait(lock, [] { return !capture_Queue.empty() || done; });
      if (done && capture_Queue.empty())
        return;

      frame = capture_Queue.front();
      capture_Queue.pop();
    }

    cv::Mat processedFrame;
    // Converting the image to grayscale.
    cv::cvtColor(frame, processedFrame,
                 cv::COLOR_BGR2GRAY);

    {
      std::lock_guard<std::mutex> lock(process_Mutex);
      process_Queue.push(processedFrame);
    }// The lock_guard is released as soon as it goes out of scope.

    process_CondVar.notify_one();
  }
}

void displayImage() {
  while (!done) {
    cv::Mat frame;

    {
      std::unique_lock<std::mutex> lock(process_Mutex);
      // The process_Mutex is used for capture_Queue object.
      process_CondVar.wait(lock, [] { return !process_Queue.empty() || done; });
      if (done && process_Queue.empty())
        return;

      frame = process_Queue.front();
      process_Queue.pop();
    }

    cv::imshow("Processed Image", frame);

    if (cv::waitKey(1) == 27) { // Exit on ESC key
      done = true;
      break;
      cv::destroyAllWindows();
    }
  }
}

int main() {
  std::thread captureThread(captureImage);
  std::thread processThread(processImage);
  std::thread displayThread(displayImage);
  
  // Join all the threads
  captureThread.join();
  processThread.join();
  displayThread.join();

  return 0;
}
