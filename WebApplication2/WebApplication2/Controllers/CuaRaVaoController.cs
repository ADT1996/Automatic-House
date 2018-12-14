using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace WebApplication2.Controllers
{
    public class CuaRaVaoController : Controller
    {
        // GET: CuaRaVao
        private static String MatKhauCua = "1234";
        public ActionResult Index()
        {
            return View();
        }

        public ActionResult DoiMatKhau()
        {
            return View(MatKhauCua);
        }

        [HttpPost]
        public ActionResult DoiMatKhau(String matKhau)
        {
            int len = matKhau.Length;
            for(int i = 0; i < len; i++)
            {
                switch(matKhau.ElementAt(i))
                {
                    case '0':
                    case '1':
                    case '2':
                    case '3':
                    case '4':
                    case '5':
                    case '6':
                    case '7':
                    case '8':
                    case '9':
                    case 'A':
                    case 'B':
                    case 'C':
                    case 'D':
                        break;
                    default:
                        ViewData["loi"] = "Sai định dạng";
                        return View(matKhau);
                }
            }
            MatKhauCua = matKhau;
            return RedirectToAction("Index","CuaRaVao");
        }
    }
}