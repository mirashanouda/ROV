from kivymd.app import MDApp
from kivy.lang import Builder
from kivy.uix.boxlayout import BoxLayout
import time

Builder.load_string('''
<CameraClick>:
    orientation: 'vertical'

    Camera:
        id: camera
        index: 4
        #resolution: (640, 480)
        play: True

    MDFillRoundFlatButton:
        text: "Button Test"
        md_bg_color: 151/255, 0, 0, 1 #background
        text_color: 1,1,1, 1
        pos_hint: {"center_x": 0.5}
        font_size: "30sp"
        #on_press: app.capture(*args)
        on_press: root.capture()
''')


class CameraClick(BoxLayout):
    i = 1
    def capture(self):
        camera = self.ids['camera']
        camera.export_to_png("IMG_{}.png".format(self.i))
        self.i += 1
        print("Captured")


class CameraFeed(MDApp):
    def __init__(self, **kwargs):
        self.title = "Camera View"
        super().__init__(**kwargs)

    def build(self):
        self.theme_cls.theme_style="Dark"
        return CameraClick()


CameraFeed().run()