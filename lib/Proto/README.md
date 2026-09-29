# Setting up Protobuf on Windows
1. Get the [.zip File](https://github.com/protocolbuffers/protobuf/releases)  
Extract it to a folder, and add the bin file to path (check to see if it has a .exe file within)  
Restart your computer, then ensure that you did this correctly by running in Powershell:  
protoc --version  <br>  
Also make sure to run this command since the zip files are a little outdated:  
pip install --upgrade protobuf  

2. Run pip install nanopb  
Once again confirm with nanopb --version

3. Add nanopb to your libdep in plaform.ini

4. Compile your files using:  
nanopb_generator -D [folder] [.proto file] <br><br>
Alternatively I've added a script called generate_proto.py that automates this every time you build. To use it just add this line to your platform.ini:  
extra_scripts =   
    pre:generate_proto.py  // This is for generating protobuf files  
    pre:generate_pio.py    // This is for generating PIO wrapper files  

5. Test your files using the python files in ProtoSim folder.


## Nice documentation on getting started with everything
[Nanopb GitHub](https://github.com/nanopb/nanopb?tab=readme-ov-file)  
[Nanopb Docs](https://jpa.kapsi.fi/nanopb/docs/) [on PlatformIO](https://registry.platformio.org/libraries/nanopb/Nanopb)  
[Protobuf Docs](https://protobuf.dev/getting-started/) [and the C++ stuff](https://protobuf.dev/getting-started/cpptutorial/)
