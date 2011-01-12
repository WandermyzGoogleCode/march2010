# Table schema: (invitation_id: integer, user: integer)
class InviteeRelation < ActiveRecord::Base
  belongs_to :invitation
  belongs_to :user
end
