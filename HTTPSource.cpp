using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Text;
using System.Threading.Tasks;

namespace HTTPTest
{
    class Program
    {
        static void Main(string[] args)
        {
            HttpWebRequest request = (HttpWebRequest)WebRequest.Create("http://www.gooogle.com");
            WebResponse response = request.GetResponse();            
            WebClient webclient = new WebClient();            

            // Create a listener.
            HttpListener listener = new HttpListener();
            
                listener.Prefixes.Add("http://localhost:8080/index/");
            
            listener.Start();
            Console.WriteLine("Listening...");
            // Note: The GetContext method blocks while waiting for a request. 
            HttpListenerContext context = listener.GetContext();
            HttpListenerRequest listenerrequest = context.Request;
            // Obtain a response object.
            HttpListenerResponse listenerresponse = context.Response;
            // Construct a response.
            string responseString = "<HTML><BODY> Hello world!</BODY></HTML>";
            byte[] buffer = System.Text.Encoding.UTF8.GetBytes(responseString);
            // Get a response stream and write the response to it.
            listenerresponse.ContentLength64 = 5000000;
            response.GetResponseStream().CopyTo(listenerresponse.OutputStream);
            //listenerresponse.OutputStream = response.GetResponseStream;
            listenerresponse.OutputStream.Flush();
            //output.Write(, 0, buffer.Length);
            //// You must close the output stream.
            //output.Close();
            listener.Stop();
        }
    }
}

//https://msdn.microsoft.com/en-us/library/system.web.httpresponse.outputstream%28v=vs.110%29.aspx
