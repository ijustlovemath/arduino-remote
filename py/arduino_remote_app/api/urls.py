from django.urls import include, path
from . import views

urlpatterns = [
    path("volume/up", views.volume_up)
]
