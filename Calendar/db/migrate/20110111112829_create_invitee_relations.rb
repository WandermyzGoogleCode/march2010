class CreateInviteeRelations < ActiveRecord::Migration
  def self.up
    create_table :invitee_relations do |t|
      t.integer :user_id
      t.integer :invitation_id

      t.timestamps
    end
  end

  def self.down
    drop_table :invitee_relations
  end
end
