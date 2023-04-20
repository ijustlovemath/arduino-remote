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
def volume_down(request):
    return JsonResponse(query("volume down"))

@api_view(["GET"])
def power_toggle(request):
    return JsonResponse(query("power"))

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
