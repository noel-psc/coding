import os
os.environ['GLOG_minloglevel'] = '2'

import cv2
import mediapipe as mp
import time

# 存储检测结果的全局变量
latest_result = None

def result_callback(result, output_image, timestamp_ms):
    """接收检测结果的回调函数"""
    global latest_result
    latest_result = result

# 初始化MediaPipe
BaseOptions = mp.tasks.BaseOptions
HandLandmarker = mp.tasks.vision.HandLandmarker
HandLandmarkerOptions = mp.tasks.vision.HandLandmarkerOptions
VisionRunningMode = mp.tasks.vision.RunningMode

# 配置检测选项
options = HandLandmarkerOptions(
    base_options=BaseOptions(model_asset_path='hand_landmarker.task'),
    running_mode=VisionRunningMode.LIVE_STREAM,
    num_hands=2,
    min_hand_detection_confidence=0.5,
    min_hand_presence_confidence=0.5,
    result_callback=result_callback
)

# 创建检测器
detector = HandLandmarker.create_from_options(options)

# 打开摄像头
cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

print("=== 手部检测程序（左右手已修正）===")
print("按 'q' 退出 | 按 's' 保存图片")

try:
    while True:
        ret, frame = cap.read()
        if not ret:
            break
        
        # 关键：先翻转图像，再检测
        frame_flipped = cv2.flip(frame, 1)  # 水平翻转（镜像）
        
        # 转换为RGB并检测
        rgb_frame = cv2.cvtColor(frame_flipped, cv2.COLOR_BGR2RGB)
        mp_image = mp.Image(image_format=mp.ImageFormat.SRGB, data=rgb_frame)
        
        current_time_ms = int(time.time() * 1000)
        detector.detect_async(mp_image, current_time_ms)
        
        # 绘制检测结果
        if latest_result and latest_result.hand_landmarks:
            for hand_idx, landmarks in enumerate(latest_result.hand_landmarks):
                # 绘制所有关键点
                for landmark in landmarks:
                    x = int(landmark.x * frame_flipped.shape[1])
                    y = int(landmark.y * frame_flipped.shape[0])
                    cv2.circle(frame_flipped, (x, y), 4, (0, 255, 0), -1)
                
                # 绘制手腕（关键点0）
                if landmarks:
                    wrist = landmarks[0]
                    wrist_x = int(wrist.x * frame_flipped.shape[1])
                    wrist_y = int(wrist.y * frame_flipped.shape[0])
                    
                    # 关键修正：获取正确的手部标签
                    if latest_result.handedness and hand_idx < len(latest_result.handedness):
                        if latest_result.handedness[hand_idx]:
                            hand_info = latest_result.handedness[hand_idx][0]
                            original_label = hand_info.category_name
                            confidence = hand_info.score
                            
                            # 修正左右手标签（因为图像被翻转了）
                            corrected_label = "Left" if original_label == "Right" else "Right"
                            
                            # 显示修正后的标签
                            cv2.putText(frame_flipped, f"{corrected_label} ({confidence:.2f})", 
                                       (wrist_x - 40, wrist_y - 20),
                                       cv2.FONT_HERSHEY_SIMPLEX, 0.6, (0, 255, 255), 2)
        
        # 显示FPS和手部数量
        hand_count = len(latest_result.hand_landmarks) if latest_result and latest_result.hand_landmarks else 0
        cv2.putText(frame_flipped, f"Hands: {hand_count}", (10, 30), 
                   cv2.FONT_HERSHEY_SIMPLEX, 0.8, (0, 255, 0), 2)
        
        # 显示当前时间
        current_time = time.strftime("%H:%M:%S")
        cv2.putText(frame_flipped, current_time, (10, 60), 
                   cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 255), 1)
        
        # 显示窗口
        cv2.imshow('Hand Detection (Left/Right Corrected)', frame_flipped)
        
        # 按键处理
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q'):
            break
        elif key == ord('s'):
            filename = f"hand_{int(time.time())}.jpg"
            cv2.imwrite(filename, frame_flipped)
            print(f"已保存: {filename}")

except KeyboardInterrupt:
    print("\n程序中断")
except Exception as e:
    print(f"错误: {e}")

finally:
    cap.release()
    cv2.destroyAllWindows()
    detector.close()
    print("程序结束")