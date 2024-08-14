# Low-Level Design: Multithreaded Image Pipeline

## 1. Threads

- **Capture Thread**: Responsible for capturing frames from the camera feed.
- **Processing Thread**: Handles processing of the captured frames (e.g., converts them to grayscale).
- **Display Thread**: Displays the processed frames in a window.

## 2. Queues

- **captureQueue**: A queue (`std::queue<cv::Mat>`) that stores frames captured by the camera, ready to be processed.
- **processQueue**: A queue (`std::queue<cv::Mat>`) that stores frames that have been processed and are ready to be displayed.

## 3. Mutexes

- **captureMutex**: A mutex (`std::mutex`) used to protect access to `captureQueue`, ensuring that only one thread modifies it at a time.
- **processMutex**: A mutex (`std::mutex`) used to protect access to `processQueue`, ensuring that only one thread modifies it at a time.

## 4. Condition Variables

- **captureCondVar**: A condition variable (`std::condition_variable`) used to signal the processing thread when a new frame is added to `captureQueue`.
- **processCondVar**: A condition variable (`std::condition_variable`) used to signal the display thread when a new processed frame is added to `processQueue`.

## 5. Main Functions

- **captureImage()**: Captures frames from the camera, locks `captureMutex`, pushes the frame into `captureQueue`, and signals the processing thread using `captureCondVar`.
- **processImage()**: Waits for frames in `captureQueue`, processes them (e.g., converts to grayscale), locks `processMutex`, pushes the processed frame into `processQueue`, and signals the display thread using `processCondVar`.
- **displayImage()**: Waits for processed frames in `processQueue`, pops them, and displays them in a window.

## 6. Data Flow

- **Capture**: `captureImage()` reads frames from the camera and pushes them onto `captureQueue`, using a mutex to prevent race conditions.
- **Processing**: `processImage()` pops frames from `captureQueue`, processes them, and pushes the results onto `processQueue`, using a mutex to ensure thread safety.
- **Display**: `displayImage()` pops frames from `processQueue` and displays them in a window.

## 7. Thread Management

- The main function creates three threads: one for each of `captureImage`, `processImage`, and `displayImage`.
- **Thread Creation**: `std::thread` is used to create threads.
- **Thread Joining**: `join()` ensures that the main function waits for all threads to complete before exiting.

## 8. Exit Condition

- The global variable `done` is used to signal all threads to stop. This flag is set to `true` when the ESC key is pressed in the display window.

## 9. Error Handling

- **Camera Error**: The program checks if the camera opens successfully.
- **Empty Frames**: The program handles empty frames during capture and skips processing if an empty frame is encountered.

## 10. Potential Issues & Considerations

- **Race Conditions**: Mutexes (`std::mutex`) are in place to prevent race conditions when accessing shared resources like `captureQueue` and `processQueue`.
- **Thread Starvation**: Although unlikely in this simple pipeline, thread starvation could occur if a thread holds a mutex for too long.
- **Memory Management**: Proper handling of `cv::Mat` objects is necessary to avoid memory leaks.
- **Performance**: While the current implementation is efficient for a basic pipeline, further optimizations (e.g., double buffering) may be required for more complex processing.
