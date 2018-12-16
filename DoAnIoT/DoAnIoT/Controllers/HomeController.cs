using System;
using System.Collections.Concurrent;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web;
using System.Web.Mvc;
using System.Web.Script.Serialization;

namespace DoAnIoT.Controllers
{
    public class NhietDoDoAm
    {
        public int nhietDo { get; set; }
        public int doAm { get; set; }
    }

    public class HomeController : Controller
    {
        private NhietDoDoAm nhietamCu;
        private static NhietDoDoAm nhietam;

        private static string led = "on";

        private static bool alarm = false;

        private bool oldalarm;

        private static bool ESP32 = false;

        private static bool ESP8266 = false;

        private static DateTime datefrom;

        private static DateTime dateTo;

        private static Dictionary<String,Boolean> dens = null;

        private BlockingCollection<string> blocking = null;

        public void ESP32_Connection()
        {
            ESP32 = true;

            while(Response.IsClientConnected) { System.Threading.Thread.Sleep(1000); }

            ESP32 = false;
        }

        public void ESP8266_Connection()
        {
            ESP8266 = true;

            while (Response.IsClientConnected) { System.Threading.Thread.Sleep(1000); }

            ESP8266 = false;
        }

        public HomeController()
        {
            if(dens == null)
            {
                dens = new Dictionary<string, bool>();
                dens["Đèn bên trái"] = false;
                dens["Đèn ở giữa"] = false;
                dens["Đèn bên phải"] = false;
            }
            if(nhietam == null)
            {
                nhietam = new NhietDoDoAm();
                nhietam.nhietDo = 0;
                nhietam.doAm = 0;
            }

            nhietamCu = new NhietDoDoAm();
            nhietamCu.nhietDo = nhietam.nhietDo;
            nhietamCu.doAm = nhietam.doAm;
            oldalarm = alarm;

            blocking = new BlockingCollection<string>();
        }

        public ActionResult Index()
        {
            ViewBag.Title = "Trang chủ";

            ViewData["status"] = (alarm ? "On" : "Off");
            ViewData["nhietDo"] = nhietamCu.nhietDo;
            ViewData["doAm"] = nhietamCu.doAm;
            
            return View(dens);
        }

        public ActionResult OnOrOffLed()
        {
            ViewData["led"] = led;
            return View();
        }

        public string setLed()
        {
            led = ("on".Equals(led) ? "off" : "on");
            //if ("on".Equals(led))
            //{
            //    led = "off";
            //}
            //else
            //{
            //    led = "on";
            //}
            return "OK";
        }

        public string demoAPI()
        {
            return led;
        }

        public ActionResult CaiDatThoiGianLamViec()
        {
            ViewData["timeFrom"] = datefrom.ToShortTimeString();
            ViewData["timeTo"] = dateTo.ToShortTimeString();
            return View();
        }

        [HttpPost]
        public ActionResult CaiDatThoiGianLamViec(String timeFrom, String timeTo)
        {
            char[] symbol = {':'};
            string[] timeF = timeFrom.Split(symbol);
            string[] timeT = timeTo.Split(symbol);
            datefrom = new DateTime(2000, 1, 1, int.Parse(timeF[0]),int.Parse(timeF[1]),0);
            dateTo = new DateTime (2000,1,1,int.Parse(timeT[0]),int.Parse(timeT[1]),0);
            return RedirectToAction("CaiDatThoiGianLamViec","Home");
        }

        public String getTimeWork()
        {
            return datefrom.Hour+ ":" + datefrom.Minute + "-" + dateTo.Hour + ":" + dateTo.Minute ;
        }

        public ActionResult Alarm()
        {
            if(alarm)
            {
                ViewData["status"] = "On";
                return View();
            }
            ViewData["status"] = "Off";
            return View();
        }

        public void setAlarm(bool status)
        {
            alarm = status;
        }

        public String getAlarm()
        {
            return alarm ? "On" : "Off";
        }

        [HttpPost]
        public string setDen(string key)
        {
            
           if (dens.ContainsKey(key))
            {
                dens[key] = !dens[key];
                return dens[key] ? "On" : "Off";
            }
            return "Error:Không tìm thấy đèn";
        }

        public String getDens()
        {
            string s = "";
            s = s + (dens.ElementAt(0).Value ? "On" : "Off");
            for (int i = 1; i < dens.Count; i++)
            {
                s = s + "-" + (dens.ElementAt(i).Value ? "On" : "Off");
            }

            return s;
        }
        
        public string setNhietDoDoAm(int nhietdo,int doAm)
        {
            nhietam.nhietDo = nhietdo;
            nhietam.doAm = doAm;
            return "OK";
        }

        //private static void ThreadResponse(HttpResponseBase response)
        //{
        //    response.ContentType = "";
        //    response.Expires = -1;
        //    response.Write("");
        //    response.Flush();
        //    System.Threading.Thread.Sleep(1000);
        //}

        public ActionResult getNhietDoDoAm()
        {
            Random rand = new Random();
            nhietam.nhietDo = rand.Next(30, 40);
            nhietam.doAm = rand.Next(45,60);
            var res = string.Empty;
            var sb = new StringBuilder();
            blocking.Add(nhietam.nhietDo.ToString());
            if(blocking.TryTake(out res,TimeSpan.FromMilliseconds(0.2))) {
                JavaScriptSerializer j = new JavaScriptSerializer();
                var serialObject = j.Serialize(new { nhietdo = nhietam.nhietDo, doAm = nhietam.doAm });
                sb.AppendFormat("data: {0}\n\n", serialObject);
            }
            return Content(sb.ToString(), "text/event-stream",Encoding.UTF8);
        }

        public void NhietDoDoAm()
        {
            Response.ContentType = "text/event-stream";
            while(true)
            {
                try
                {
                    if(nhietamCu.nhietDo != nhietam.nhietDo || nhietamCu.doAm != nhietam.doAm)
                    {
                        Response.Write("data: " + nhietam.nhietDo + "-" + nhietam.doAm + "\n\n");
                        Response.Flush();
                        nhietamCu.nhietDo = nhietam.nhietDo;
                        nhietamCu.doAm = nhietam.doAm;
                    }
                    if(!Response.IsClientConnected)
                    {
                        Response.Close();
                        return;
                    }
                    System.Threading.Thread.Sleep(200);
                } catch (HttpException)
                {
                    Response.Close();
                    return;
                }
            }
        }

        public void SyncDens()
        {
            Response.ContentType = "text/event-stream";

            Dictionary<String, Boolean> denCus = new Dictionary<String, Boolean>();

            for(int i = 0; i < dens.Count; i++)
            {
                denCus[dens.ElementAt(i).Key] = dens[dens.ElementAt(i).Key];
            }

            while (true)
            {
                try
                {
                    int i;

                    for(i = 0; i < dens.Count; i++)
                    {
                        if (dens.ElementAt(i).Value != denCus.ElementAt(i).Value)
                        {
                            denCus[denCus.ElementAt(i).Key] = dens[dens.ElementAt(i).Key];
                            string data = "data: ";
                            data += i + "-" + (denCus.ElementAt(i).Value ? "On" : "Off");
                            data += "\n\n";
                            Response.Write(data);
                            Response.Flush();
                            break;
                        }
                    }

                    if (!Response.IsClientConnected)
                    {
                        Response.Close();
                        return;
                    }
                    System.Threading.Thread.Sleep(200);
                }
                catch (HttpException)
                {
                    Response.Close();
                    return;
                }
            }
        }

        public void setOnOffAllDens(bool status)
        {
            int count = dens.Count;
            for (int i = 0; i < count; i++)
            {
                dens[dens.ElementAt(i).Key] = status;
            }
        }

        public void SyncAlarm()
        {
            Response.ContentType = "text/event-stream";
            while(Response.IsClientConnected)
            {
                try
                {
                    if(oldalarm != alarm)
                    {
                        oldalarm = alarm;
                        Response.Write("data: " + (alarm ? "On" : "Off") + "\n\n");
                        Response.Flush();
                    }
                } catch (HttpException)
                {
                    Response.Close();
                    return;
                }
            }
            Response.Close();
        }
    }
}