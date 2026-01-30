import cv2
import mediapipe as mp
import time
import os

# 下载模型（如果不存在）
model_path = "hand_landmarker.task"
model_url = "https://storage.googleapis.com/mediapipe-models/hand_landmarker/hand_landmarker/float16/1/hand_landmarker.task"

if not os.path.exists(model_path):
    print("正在下载手部检测模型...")
    import urllib.request
    urllib.request.urlretrieve(model_url, model_path)
    print("模型下载完成！")

# 全局变量存储检测结果
latest_result = None

def result_callback(result, output_image, timestamp_ms):
    """接收检测结果的回调函数"""
    global latest_result
    latest_result = result

# 初始化检测器
BaseOptions = mp.tasks.BaseOptions
HandLandmarker = mp.tasks.vision.HandLandmarker
HandLandmarkerOptions = mp.tasks.vision.HandLandmarkerOptions
VisionRunningMode = mp.tasks.vision.RunningMode

options = HandLandmarkerOptions(
    base_options=BaseOptions(model_asset_path=model_path),
    running_mode=VisionRunningMode.LIVE_STREAM,
    num_hands=2,
    min_hand_detection_confidence=0.5,
    result_callback=result_callback
)

# 创建检测器
detector = HandLandmarker.create_from_options(options)

# 开启摄像头
cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

print("=== 简单手部检测程序 ===")
print("按 'q' 退出程序")
print("按 's' 保存当前图片")

fps_time = time.time()
frame_count = 0

try:
    while True:
        # 读取摄像头
        ret, frame = cap.read()
        if not ret:
            break
        
        # 转换图像格式并发送检测
        rgb_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        mp_image = mp.Image(image_format=mp.ImageFormat.SRGB, data=rgb_frame)
        
        current_time_ms = int(time.time() * 1000)
        detector.detect_async(mp_image, current_time_ms)
        
        # 如果有检测结果，绘制到图像上
        if latest_result and latest_result.hand_landmarks:
            num_hands = len(latest_result.hand_landmarks)
            
            # 绘制每只手的关键点
            for hand_idx, landmarks in enumerate(latest_result.hand_landmarks):
                # 绘制关键点
                for landmark in landmarks:
                    x = int(landmark.x * frame.shape[1])
                    y = int(landmark.y * frame.shape[0])
                    cv2.circle(frame, (x, y), 5, (0, 255, 0), -1)
                
                # 绘制手腕位置
                wrist = landmarks[0]
                wrist_x = int(wrist.x * frame.shape[1])
                wrist_y = int(wrist.y * frame.shape[0])
                cv2.circle(frame, (wrist_x, wrist_y), 10, (255, 0, 0), 2)
                
                # 显示左右手信息
                if latest_result.handedness and hand_idx < len(latest_result.handedness):
                    if latest_result.handedness[hand_idx]:
                        hand_info = latest_result.handedness[hand_idx][0]
                        label = hand_info.category_name
                        confidence = hand_info.score
                        cv2.putText(frame, f"{label} ({confidence:.2f})", 
                                   (wrist_x - 40, wrist_y - 20),
                                   cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 255), 2)
        
        # 计算FPS
        frame_count += 1
        if frame_count % 30 == 0:
            fps = 30 / (time.time() - fps_time)
            fps_time = time.time()
            print(f"FPS: {fps:.1f} | 检测到的手: {len(latest_result.hand_landmarks) if latest_result and latest_result.hand_landmarks else 0}")
        
        # 显示手部数量
        hand_count = len(latest_result.hand_landmarks) if latest_result and latest_result.hand_landmarks else 0
        cv2.putText(frame, f"Hands: {hand_count}", (10, 30), 
                   cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)
        
        # 显示图像
        cv2.imshow('Live Hand Detection', frame)
        
        # 按键处理
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q'):
            break
        elif key == ord('s'):
            # 保存当前帧
            filename = f"hand_detect_{int(time.time())}.jpg"
            cv2.imwrite(filename, frame)
            print(f"图片已保存: {filename}")

except KeyboardInterrupt:
    print("\n程序被用户中断")

finally:
    # 清理资源
    detector.close()
    cap.release()
    cv2.destroyAllWindows()
    print("程序结束")