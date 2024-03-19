from django.urls import include, path
from . import views

urlpatterns = [
    path("volume/up", views.volume_up),
    path("volume/down", views.volume_down),
    path("power/toggle", views.power_toggle),
    path("restart/spotify", views.restart_spotify),
    path("remote/up", views.remote_up),
    path("remote/down", views.remote_down),
    path("remote/left", views.remote_left),
    path("remote/right", views.remote_right),
    path("remote/ok", views.remote_ok),
    path("remote/enter", views.remote_enter),
    path("remote/menu", views.remote_menu),
    path("remote/exit", views.remote_exit),
    path("remote/repeat", views.remote_repeat),
]
