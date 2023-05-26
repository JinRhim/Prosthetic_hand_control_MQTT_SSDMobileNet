import os
import random
import shutil


def split_dataset(folder_name, train_percentage):
    # Get all image filenames in the specified folder
    filenames = []
    for filename in os.listdir(folder_name):
        if filename.endswith('.jpg'):
            filenames.append(filename.split('.jpg')[0])

    # Shuffle the filenames
    random.shuffle(filenames)

    # Split the filenames into train and test sets
    split_index = int(len(filenames) * train_percentage)
    train_filenames = filenames[:split_index]
    test_filenames = filenames[split_index:]

    # Create the train and test directories if they don't exist
    if not os.path.exists('train'):
        os.makedirs('train')
    if not os.path.exists('test'):
        os.makedirs('test')

    # Copy the train images and XML files to the train directory
    for filename in train_filenames:
        image_path = os.path.join(folder_name, f'{filename}.jpg')
        xml_path = os.path.join(folder_name, f'{filename}.xml')
        shutil.copy(image_path, 'train')
        shutil.copy(xml_path, 'train')

    # Copy the test images and XML files to the test directory
    for filename in test_filenames:
        image_path = os.path.join(folder_name, f'{filename}.jpg')
        xml_path = os.path.join(folder_name, f'{filename}.xml')
        shutil.copy(image_path, 'test')
        shutil.copy(xml_path, 'test')


# Main =======================================
split_dataset('apple', 0.8)
split_dataset('hand', 0.8)
