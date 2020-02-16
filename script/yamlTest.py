import yaml
import ntpath

with open("./config.yaml", "r") as stream:
	try:
		dataloaded = yaml.load(stream)
	except yaml.YAMLError as exc:
		print(exc)

print ntpath.join(
	dataloaded["neural_network"]["path"],
	dataloaded["neural_network"]["neural_network_name"]+".txt"
)