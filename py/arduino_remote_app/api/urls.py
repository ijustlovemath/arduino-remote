from django.urls import include, path
from . import views

urlpatterns = [
    path("volume/up", views.volume_up),
    path("volume/down", views.volume_down),
    path("power/toggle", views.power_toggle),
    path("restart/spotify", views.restart_spotify),
]
