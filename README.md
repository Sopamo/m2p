# m2p
An unintuitive way to convert movies into images

## Setup

 - Install [CocoaPods](https://cocoapods.org/)
 - Run pod install in the project root
 - Launch the project with the .xcworkspace file in Xcode
 - Add 2 launch arguments in Xcode: absolute paths to: input file(avi) and ouput folder
 - Product -> Scheme -> Edit Scheme -> Run -> Arguments -> Arguments passen on launch

## Todo

 - Decoding currently works only with input files < 64mb
 - Add encryption
 - Figure out a way to store the input data length to not have a blob of empty data at the end of the output file
 - Split the program in 2 separate commands