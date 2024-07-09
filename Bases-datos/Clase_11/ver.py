import subprocess

sub = subprocess.run(["pip", "list", '--disable-pip-version-check'],
                    stdout=subprocess.PIPE,
                    universal_newlines=True
                    )
pkgs = (line.rstrip().split() for line in sub.stdout.split("\n")[2: -1])

for paquete, version in pkgs:
    print(paquete, version)