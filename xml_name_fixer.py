import xml.etree.ElementTree as ET
import os

# Fix the name tag
# Delete the program that does not have nametag


def fix_filename_tags(data_dir):
    """
    Loops through all .xml files in the specified directory and updates the filename tag to match the file name
    (without the .xml extension).
    """
    for xml_file in os.listdir(data_dir):
        if xml_file.endswith(".xml"):
            # Get the filename from the file path
            filename = os.path.splitext(xml_file)[0]

            # Parse the .xml file and update the filename tag
            tree = ET.parse(os.path.join(data_dir, xml_file))
            root = tree.getroot()
            root.find("filename").text = filename

            # Write the updated XML back to the file
            tree.write(os.path.join(data_dir, xml_file))
            print(f'Fixed file for non-matching filename tag: {filename}')


# Set the path to your dataset folder
data_dir = input("Enter file name: ")

# Loop through all files in the dataset directory
print(f'Trial 1: No nametag deleter working....')

for filename in os.listdir(data_dir):
    if filename.endswith(".xml"):
        # Parse the XML file and check if it has a <name> tag
        xml_path = os.path.join(data_dir, filename)
        tree = ET.parse(xml_path)
        root = tree.getroot()
        has_name_tag = False
        for obj in root.findall("object"):
            if obj.find("name") is not None:
                has_name_tag = True
                break

        # If the XML file doesn't have a <name> tag, delete it and its corresponding JPG file
        if not has_name_tag:
            jpg_filename = filename.replace(".xml", ".jpg")
            jpg_path = os.path.join(data_dir, jpg_filename)
            print(
                f'Name tag does not exist for {filename}\n {jpg_path}\n {xml_path}')
            os.remove(xml_path)
            if os.path.exists(jpg_path):
                os.remove(jpg_path)


print("Trial 2: Remove .jpg from the filename\n")

# Iterate over all XML files in the specified folder
for filename in os.listdir(data_dir):
    if filename.endswith('.xml'):
        filepath = os.path.join(data_dir, filename)
        tree = ET.parse(filepath)
        root = tree.getroot()

        # Find the filename tag and remove the .jpg extension
        for filename_tag in root.iter('filename'):
            filename_tag.text = os.path.splitext(filename_tag.text)[0]

        # Write the modified XML back to the file
        tree.write(filepath)


print("\nTrial 3: filename tag fixer working\n")
fix_filename_tags(data_dir)
