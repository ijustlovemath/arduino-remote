from django.shortcuts import render
from django.http import JsonResponse
from rest_framework.decorators import api_view

import subprocess
import os

from .remote import query


# Used a lot from here: https://dev.to/nobleobioma/create-a-simple-rest-api-with-django-253p
@api_view(["GET"])
def volume_up(request):
    content = query("volume up")
    return JsonResponse(content)

@api_view(["GET"])
def remote_repeat(request):
    return JsonResponse(query(""))

@api_view(["GET"])
def volume_down(request):
    return JsonResponse(query("volume down"))

@api_view(["GET"])
def power_toggle(request):
    return JsonResponse(query("power"))

@api_view(["GET"])
def remote_up(request):
    return JsonResponse(query("up"))

@api_view(["GET"])
def remote_down(request):
    return JsonResponse(query("down"))

@api_view(["GET"])
def remote_left(request):
    return JsonResponse(query("left"))

@api_view(["GET"])
def remote_right(request):
    return JsonResponse(query("right"))

@api_view(["GET"])
def remote_ok(request):
    return JsonResponse(query("ok"))

@api_view(["GET"])
def remote_enter(request):
    return JsonResponse(query("enter"))

@api_view(["GET"])
def remote_exit(request):
    return JsonResponse(query("exit"))

@api_view(["GET"])
def remote_menu(request):
    return JsonResponse(query("menu"))

@api_view(["GET"])
def restart_spotify(request):
    resp = None
    try:
        command = "gtk-launch spotify"
        #command = "su jer 'pkill spotify; sleep 1; gtk-launch spotify &'"
        #print(os.environ['XAUTHORITY'])
        ret = os.system(command)

        #proc = subprocess.Popen(command.split(), stdout=subprocess.PIPE)
        #ret = '##'.join(line for line, _ in zip(proc.stdout, range(3)))
        resp = dict(status="success", code=ret, disp=os.environ.get('DISPLAY', 'unknown display'))
    except Exception as e:
        resp = dict(status="failure", error=str(e), xauth=os.environ.get('XAUTHORITY', 'No XAuthority available'))
        
    return JsonResponse(resp)
