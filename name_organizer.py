import os
import xml.etree.ElementTree as ET


def rename_files(folder_name, category_name):
    # Check if the folder exists
    if not os.path.isdir(folder_name):
        print(f"Folder '{folder_name}' does not exist.")
        return

    # Get a list of all files in the folder
    files = os.listdir(folder_name)

    # Counter for numbering the files
    counter = 1

    # Iterate over the files in the folder
    for file in files:
        # Check if the file is a .jpg or .xml file
        if file.endswith(".jpg"):
            # Rename the .jpg file
            old_path = os.path.join(folder_name, file)
            new_filename = f"{category_name}_{counter}.jpg"
            new_path = os.path.join(folder_name, new_filename)
            os.rename(old_path, new_path)

            # Update the corresponding .xml file
            xml_file = file.replace(".jpg", ".xml")
            xml_path = os.path.join(folder_name, xml_file)

            # Check if the .xml file exists
            if os.path.isfile(xml_path):
                new_xml_filename = new_filename[:-4] + ".xml"
                new_xml_path = os.path.join(folder_name, new_xml_filename)
                os.rename(xml_path, new_xml_path)
                # Parse the XML file
                tree = ET.parse(new_xml_path)
                root = tree.getroot()

                # Update the <filename> tag in the XML file
                filename_element = root.find("filename")
                filename_element.text = new_filename[:-4]

                # Save the modified XML file
                tree.write(new_xml_path)

            # Increment the counter
            counter += 1

    print("Files renamed successfully.")


# Prompt the user to enter the folder name
print("This program will change the .jpg image name and .xml name")
print("This program will change .xml <filename></filename> so that it matches the .jpg name")
print("Fix the <filename> issue by running xml_name_fixer.py")
folder_name = input("\nEnter the folder name: ")
category_name = input("Enter object category (hand, apple, marker, ...etc): ")

# Call the function to rename the files
rename_files(folder_name, category_name)
