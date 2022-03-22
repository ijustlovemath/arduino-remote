from django.contrib import admin
from django.urls import path, include

print('hey there stanger')

urlpatterns = [
    path('admin/', admin.site.urls),
    path('api/', include('api.urls')),
]
