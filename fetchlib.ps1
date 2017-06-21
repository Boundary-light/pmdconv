Add-Type -AssemblyName System.IO.Compression.FileSystem

function Unzip
{
	param([string]$zipfile, [string]$outpath)
	[System.IO.Compression.ZipFile]::ExtractToDirectory($zipfile, $outpath)
}

#����midifile�⵽�ļ�����
$webc = New-Object System.Net.WebClient
if(!(Test-Path "$PSScriptRoot\midifile.zip"))
{
	echo "���� midifile..."
	$webc.DownloadFile("https://github.com/craigsapp/midifile/zipball/master","$PSScriptRoot\midifile.zip")
}
if(!(Test-Path "$PSScriptRoot\pmdplay.zip"))
{
	echo "���� pmdplay..."
	$webc.DownloadFile("https://github.com/lxfly2000/pmdplay/archive/master.zip","$PSScriptRoot\pmdplay.zip")
}

Unzip "midifile.zip" "."
Unzip "pmdplay.zip" "."
if(Test-Path "midifile")
{
	rd -Recurse "midifile"
}
move "*midifile-*" "midifile"
if(Test-Path "pmdplay")
{
	rd -Recurse "pmdplay"
}
move "*pmdplay-*" "pmdplay"
del pmdplay\pmdplay.vcxproj
copy pmdplay.vcxproj pmdplay\

#����MSBuild
$path = &"${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -latest -products * -requires Microsoft.Component.MSBuild -property installationPath
$path = join-path $path 'MSBuild\15.0\Bin\MSBuild.exe'

#����Lib
&$path midifile\visual-studio\midifile.vcxproj "/p:Configuration=Debug;Platform=Win32;PlatformToolset=v141;WindowsTargetPlatformVersion=10.0.14393.0"
&$path midifile\visual-studio\midifile.vcxproj "/p:Configuration=Release;Platform=Win32;PlatformToolset=v141;WindowsTargetPlatformVersion=10.0.14393.0"
&$path pmdplay "/p:Configuration=Debug;Platform=Win32;PlatformToolset=v141;WindowsTargetPlatformVersion=10.0.14393.0;CharacterSet=MultiByte"
&$path pmdplay "/p:Configuration=Release;Platform=Win32;PlatformToolset=v141;WindowsTargetPlatformVersion=10.0.14393.0;CharacterSet=MultiByte"
md bin
move pmdplay\Release\pmdplay.dll .\bin

#����������
&$path pmdconv.vcxproj "/p:Configuration=Release;Platform=Win32"
move Release\pmdconv.exe .\bin