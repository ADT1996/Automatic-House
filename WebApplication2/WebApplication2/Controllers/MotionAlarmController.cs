using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace WebApplication2.Controllers
{
    public class MotionAlarmController : Controller
    {
        //GET: MotionAlarm
        //public ActionResult Index()
        //{
        //    return View();
        //}
        static string alarm;
        public ActionResult ControllAlarm()
        {
          ViewData["alarm"] = alarm;
            return View();
        }

        public string setAlarm(string _alarm)
        {
            if ("Auto".Equals(_alarm))
            {
                alarm = "1";
            }
            else if ("Turn On".Equals(_alarm))
            {
                alarm = "2";
            }
            else
            {
                alarm = "3";
            }
            return "OK";
        }

        public string demo()
        {
            return alarm;
        }
    }
}