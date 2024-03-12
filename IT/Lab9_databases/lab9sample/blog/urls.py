from django.conf.urls import include
from django.urls import re_path as url

from django.contrib import admin

admin.autodiscover()

urlpatterns = [
    url(r'^blog/', include('blog.urls')),
    url(r'^admin/', include(admin.site.urls)),
]
