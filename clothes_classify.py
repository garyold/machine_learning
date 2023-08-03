# Download dataset
!gdown --id '1ieM_YfjPAPPDFZCZnMvOLLRabFnLr_oo' --output 2020-intro-to-ml-and-dl-findal-project.zip
!unzip "/content/2020-intro-to-ml-and-dl-findal-project.zip"

#Data input
import pandas as pd
import os
from tensorflow.keras.preprocessing.image import ImageDataGenerator

base_dir = "/content/train"
train_dir = os.path.join(base_dir, "train")

train_files = pd.read_csv("train_data.csv",dtype=str)

#Data augmentation
from tensorflow.keras.preprocessing.image import ImageDataGenerator

train_datagen = ImageDataGenerator(rescale=1./255.,
rotation_range=40,
width_shift_range=0.2,
height_shift_range=0.2,
zoom_range=0.2,
horizontal_flip=True,
validation_split=0.2)

validation_datagen = ImageDataGenerator(rescale=1./255.,validation_split=0.2)

#Data generator
train_generator = train_datagen.flow_from_dataframe(
    dataframe=train_files,
    directory=train_dir,
    x_col='Name', 
    y_col='Type', 
    class_mode='categorical',   
    subset='training',
    shuffle=False,
    target_size=(150,150),
    batch_size=60)

validation_generator = validation_datagen.flow_from_dataframe(
    dataframe=train_files,
    directory=train_dir,
    x_col='Name', 
    y_col='Type', 
    class_mode='categorical',   
    subset='validation',
    shuffle=False,
    target_size=(150,150),
    batch_size=60)

#VGG16
from tensorflow.keras.applications import VGG16

conv_base = VGG16(weights='imagenet',
                  include_top=False,
                  input_shape=(150, 150, 3))
conv_base.summary()

from tensorflow.keras import models
from tensorflow.keras import layers
from keras.regularizers import l2

model = models.Sequential()
model.add(conv_base)
model.add(layers.Flatten())
model.add(layers.Dense(512, activation='relu'))
model.add(layers.Dense(512, activation='relu'))
model.add(layers.Dense(256, activation='relu'))
model.add(layers.Dense(256, kernel_regularizer=l2(0.001), activation='relu'))
model.add(layers.Dropout(0.5))
model.add(layers.Dense(4,  activation='softmax'))

from tensorflow.keras import optimizers

model.compile(loss='categorical_crossentropy',
              optimizer=optimizers.Adam(lr=1e-4),
              metrics=['acc'])

from keras.callbacks import EarlyStopping, ModelCheckpoint

earlystop = EarlyStopping(monitor='val_acc', patience=5, verbose=1)

history = model.fit(
train_generator,
steps_per_epoch = train_generator.samples // 60,
epochs=100,
validation_data=validation_generator,
validation_steps = validation_generator.samples // 60,
callbacks = [earlystop])

import matplotlib.pyplot as plt
def figure(epochs, history, train, validation, type):
    epochs = range(1, epochs+1)
    plt.plot(epochs, history.history[train], 'b-')
    plt.plot(epochs, history.history[validation], 'bo')
    plt.xlabel('Epochs')
    if type == 'loss':
        plt.ylabel('loss')
    if type == 'accuracy':
        plt.ylabel('accuracy')
    plt.legend([train, validation])
    plt.show()
figure(22, history, 'acc', 'val_acc', type='accuracy')
figure(22, history, 'loss', 'val_loss', type='loss')

#Save the network
model.save_weights('cnn.h5')

#Test
import cv2

test_path='test/test/'
allFileList = os.listdir(test_path)
test = []
# 逐一查詢檔案清單

for file in allFileList:
  img=cv2.imread(test_path + str(file))
  image = cv2.resize(img, (150, 150), interpolation=cv2.INTER_AREA)
  image = cv2.cvtColor(image,cv2.COLOR_BGR2RGB)
  image = image.astype('float32')/255.0
  test.append([file, image])

import numpy as np

X_predict = []
for i in range(len(test)):
  X_predict.append(test[i][1])
X_predict = np.array(X_predict)

#predict
y_predict = model.predict(X_predict)

predict = []
for i in y_predict:
#   print(np.argmax(i))
  predict.append(np.argmax(i))

#export
import csv
with open('output9475_9625.csv', 'w', newline='') as csvfile:
    # 建立 CSV 檔寫入器
    writer = csv.writer(csvfile)
    writer.writerow(['Name', 'Type'])
    for i in range(len(test)):
        writer.writerow([test[i][0], predict[i]])
