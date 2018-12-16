using Microsoft.Owin;
using Owin;

[assembly: OwinStartupAttribute(typeof(DoAnIoT.Startup))]
namespace DoAnIoT
{
    public partial class Startup
    {
        public void Configuration(IAppBuilder app)
        {
            ConfigureAuth(app);
        }
    }
}
