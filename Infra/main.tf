terraform {
	required_version = ">= 0.14.0"
	required_providers {
		openstack = { 
			source = "terraform-provider-openstack/openstack"
			version = "1.49.0"
		}
		cloudinit = {
			source = "hashicorp/cloudinit"
			version = "2.2.0"
		}
	}
}

data "cloudinit_config" "user_data" {
  part {
    content_type = "text/cloud-config"
    content = <<EOF
#cloud-config
runcmd:
  - echo "Hello from cloud-init" > /tmp/hello.txt
  - curl -s http://10.20.22.18:8080/v1/AUTH_4b315635c6a0412198f0638b8edcced9/zz3-tp4/hello-api -o /usr/local/bin/hello-api
  - chmod +x /usr/local/bin/hello-api
  - echo "[Unit]
Description=Hello API Service
After=network.target

[Service]
ExecStart=/usr/local/bin/hello-api
Restart=always

[Install]
WantedBy=multi-user.target" > /etc/systemd/system/hello-api.service
  - systemctl daemon-reload
  - systemctl enable hello-api.service
  - systemctl start hello-api.service
EOF
  }
}

provider "openstack" {}

resource "openstack_compute_instance_v2" "hello_vm"{
	name = "hello-aoxie"
	flavor_name = "small-1c-1gb"
	image_id = "3d3cea93-bc21-410d-9b98-e870da8b2098"
	key_pair = "TP4_Key"
	security_groups = ["default"]
	user_data = data.cloudinit_config.user_data.rendered
	network {
		name = "aoxie_network"
	}	
}


