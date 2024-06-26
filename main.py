from flask import Flask, render_template, Response, request, send_from_directory
from camera import VideoCamera
import os
import serial

ser = serial.Serial('/dev/ttyACM0', 9600)

pi_camera = VideoCamera(flip=False) # flip pi camera if upside down.

def camera_main():
        # App Globals (do not edit)
        app = Flask(__name__)

        @app.route('/')
        def index():
            return render_template('index.html') #you can customze index.html here

        def gen(camera):
            #get camera frame
            while True:
                frame = camera.get_frame()
                yield (b'--frame\r\n'
                       b'Content-Type: image/jpeg\r\n\r\n' + frame + b'\r\n\r\n')

        @app.route('/video_feed')
        def video_feed():
            return Response(gen(pi_camera),
                            mimetype='multipart/x-mixed-replace; boundary=frame')

        # Take a photo when pressing camera button
        @app.route('/picture')
        def take_picture():
            pi_camera.take_picture()
            return "None"

        if __name__ == '__main__':

            app.run(host='0.0.0.0', debug=False)


while True:
        read_serial = ser.readline().strip()
        print(str(read_serial))
        if(read_serial == b'0'):
                print("camera")
                camera_main()

