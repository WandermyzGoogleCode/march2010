# Table schema: (extra_info: string, timestamp: integer, event_id: integer)
# "timestamp" here is for garbage collection, i.e. for deleting old invitations.
# Maybe this can be done by created_at:datetime.
class Invitation < ActiveRecord::Base
  belongs_to :event
  has_one :invitor_relation, :class_name => "InvitorRelation", :dependent => :destroy
  has_many :invitee_relation, :class_name => "InviteeRelation", :dependent => :destroy
end
