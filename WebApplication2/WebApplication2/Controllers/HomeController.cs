using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace WebApplication2.Controllers
{
    public class HomeController : Controller
    {
        static string led = "on";
        public ActionResult Index()
        {
            ViewBag.Title = "Home Page";

            return View();
        }

        public ActionResult OnOrOffLed()
        {
            ViewData["led"] = led;
            return View();
        }

        public string setLed()
        {
            if ("on".Equals(led))
            {
                led = "off";
            }
            else
            {
                led = "on";
            }
            return "OK";
        }

        public string demoAPI()
        {
            return led;
        }
    }
}
