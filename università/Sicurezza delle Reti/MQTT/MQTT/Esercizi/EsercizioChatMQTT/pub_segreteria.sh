#!/bin/bash
mosquitto_pub -h e0d996a0720a4a25ae1a34becc9e8a90.s1.eu.hivemq.cloud -p 8883 -u univr-studenti -P MQTT-esercitazione2026 -t "messaggi/segreteria/ufficio1" -m "Scadenza iscrizioni prorogata"
