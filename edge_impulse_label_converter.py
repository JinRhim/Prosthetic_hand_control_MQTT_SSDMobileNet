import xml.etree.ElementTree as ET
import json
import os

# Set the path to your dataset folder
data_dir = input("Enter folder name: ")

# Create an empty dictionary to store the bounding box data
bounding_boxes = {}

# Loop through all .xml files in the data directory
for xml_file in os.listdir(data_dir):
    if xml_file.endswith(".xml"):
        # Parse the .xml file and extract the relevant information
        tree = ET.parse(os.path.join(data_dir, xml_file))
        root = tree.getroot()
        filename = root.find("filename").text + ".jpg"
        boxes = []
        for obj in root.findall("object"):
            label = obj.find("name").text
            xmin = int(round(float(obj.find("bndbox").find("xmin").text)))
            ymin = int(round(float(obj.find("bndbox").find("ymin").text)))
            xmax = int(round(float(obj.find("bndbox").find("xmax").text)))
            ymax = int(round(float(obj.find("bndbox").find("ymax").text)))
            box = {"x": xmin, "y": ymin, "width": xmax -
                   xmin, "height": ymax - ymin, "label": label}
            boxes.append(box)

        bounding_boxes[filename] = boxes

# Create the output dictionary
output = {"version": 1, "type": "bounding-box-labels",
          "boundingBoxes": bounding_boxes}

# Write the output to a file in the same directory as the script
output_file = os.path.join(os.path.dirname(__file__), "bounding_boxes.labels")
with open(output_file, "w") as outfile:
    json.dump(output, outfile, indent=4)
