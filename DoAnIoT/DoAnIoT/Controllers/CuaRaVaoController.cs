using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace DoAnIoT.Controllers
{
    public class CuaRaVaoController : Controller
    {
        // GET: CuaRaVao
        private static String matKhauCua = "1234";
        private static Boolean isOpen = false;
        public ActionResult Index()
        {
            return View();
        }

        public ActionResult MoCua()
        {
            ViewData["matKhau"] = "";
            return View();
        }

        [HttpPost]
        public ActionResult MoCua(String matKhau)
        {
            if(matKhau == matKhauCua)
            {
                isOpen = true;
                ViewData["thongBao"] = "Mở cửa thành cônng";
                ViewData["matKhau"] = "";
                return View();
            }

            isOpen = false;
            ViewData["thongBao"] = "Mật khẩu không đúng";
            ViewData["matKhau"] = matKhau;
            return View();
        }

        public Boolean isMoCua()
        {
            if(isOpen)
            {
                isOpen = false;
                return !isOpen;
            }
            return isOpen;
        }

        [HttpGet]
        public ActionResult DoiMatKhau()
        {
            ViewData["matKhau"] = matKhauCua;
            return View();
        }

        [HttpPost]
        public ActionResult DoiMatKhau(String matKhau)
        {
            int len = matKhau.Length;
            for (int i = 0; i < len; i++)
            {
                switch (matKhau.ElementAt(i))
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
                        ViewData["matKhau"] = matKhau;
                        return View();
                }
            }
            matKhauCua = matKhau;
            return RedirectToAction("Index", "Home");
        }

        public String MatKhauCua()
        {
            return matKhauCua;
        }
    }
}