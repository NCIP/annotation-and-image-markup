#region License

//L
// 2007 - 2013 Copyright Northwestern University
//
// Distributed under the OSI-approved BSD 3-Clause License.
// See http://ncip.github.com/annotation-and-image-markup/LICENSE.txt for details.
//L

#endregion

using System;
using System.Collections;
using System.IO;
using ICSharpCode.SharpZipLib.Zip;

namespace SearchComponent
{
    public static class ZipUtil
    {
        public static void ZipFiles(string inputFolderPath, string outputPathAndFile, string password)
        {
            ArrayList ar = GenerateFileList(inputFolderPath); // generate file list
            int TrimLength = (Directory.GetParent(inputFolderPath)).ToString().Length;
            // find number of chars to remove     // from orginal file path
            TrimLength += 1; //remove '\'
            FileStream ostream;
            byte[] obuffer;
            string outPath = inputFolderPath + @"\" + outputPathAndFile;
            ZipOutputStream oZipStream = new ZipOutputStream(File.Create(outPath)); // create zip stream
            if (!string.IsNullOrEmpty(password))
                oZipStream.Password = password;
            oZipStream.SetLevel(9); // maximum compression
            ZipEntry oZipEntry;
            foreach (string Fil in ar) // for each file, generate a zipentry
            {
                oZipEntry = new ZipEntry(Fil.Remove(0, TrimLength));
                oZipStream.PutNextEntry(oZipEntry);

                if (!Fil.EndsWith(@"/")) // if a file ends with '/' its a directory
                {
                    ostream = File.OpenRead(Fil);
                    obuffer = new byte[ostream.Length];
                    ostream.Read(obuffer, 0, obuffer.Length);
                    oZipStream.Write(obuffer, 0, obuffer.Length);
                }
            }
            oZipStream.Finish();
            oZipStream.Close();
        }


        private static ArrayList GenerateFileList(string Dir)
        {
            ArrayList fils = new ArrayList();
            bool Empty = true;
            foreach (string file in Directory.GetFiles(Dir)) // add each file in directory
            {
                fils.Add(file);
                Empty = false;
            }

            if (Empty)
            {
                if (Directory.GetDirectories(Dir).Length == 0)
                    // if directory is completely empty, add it
                {
                    fils.Add(Dir + @"/");
                }
            }

            foreach (string dirs in Directory.GetDirectories(Dir)) // recursive
            {
                foreach (object obj in GenerateFileList(dirs))
                {
                    fils.Add(obj);
                }
            }
            return fils; // return file list
        }

        public static void UnZipFiles(string zipPathAndFile, string outputFolder, string password, bool deleteZipFile)
        {
            UnZipFiles(zipPathAndFile, outputFolder, password, deleteZipFile, false);
        }

        public static void UnZipFiles(string zipPathAndFile, string outputFolder, string password, bool deleteZipFile, bool ignoreFolderNames)
        {
            ZipInputStream s = new ZipInputStream(File.OpenRead(zipPathAndFile));
            if (!string.IsNullOrEmpty(password))
                s.Password = password;
            ZipEntry theEntry;
            while ((theEntry = s.GetNextEntry()) != null)
            {
                string directoryName = outputFolder;
                string fileName = Path.GetFileName(theEntry.Name);
                // create directory 
                if (directoryName != "")
                {
                    Directory.CreateDirectory(directoryName);
                }
                if (fileName != String.Empty)
                {
                    if (theEntry.Name.IndexOf(".ini") < 0)
                    {
                        string fullPath;
                        if (ignoreFolderNames) 
                            fullPath = Path.Combine(directoryName, fileName);
                        else 
                            fullPath = Path.Combine(directoryName, theEntry.Name);
                        fullPath = fullPath.Replace("\\ ", "\\");
                        string fullDirPath = Path.GetDirectoryName(fullPath);
                        if (!Directory.Exists(fullDirPath)) Directory.CreateDirectory(fullDirPath);
                        FileStream streamWriter = File.Create(fullPath);
                        int size = 2048;
                        byte[] data = new byte[2048];
                        while (true)
                        {
                            size = s.Read(data, 0, data.Length);
                            if (size > 0)
                            {
                                streamWriter.Write(data, 0, size);
                            }
                            else
                            {
                                break;
                            }
                        }
                        streamWriter.Close();
                    }
                }
            }
            s.Close();
            if (deleteZipFile)
                File.Delete(zipPathAndFile);
        }
    }
}
